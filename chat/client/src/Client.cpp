#include "Client.h" 
#include <vector>
#include <openssl/evp.h>    // EVP_CIPHER_CTX, EVP_EncryptInit_ex и т.д.
#include <openssl/rand.h>   // RAND_bytes
void Client::run() {
	UInt256 privateKey = UInt256::generateKey();
	UInt256 publicKey = ScalarMult(privateKey, UInt256::basePoint());
	cout << "Подключение" << endl;
	auto results = resolver_.resolve(host_, port_);
	net::connect(socket.next_layer(), results);
	cout << "Подключено" << endl;
	net::write(socket.next_layer(), net::buffer(publicKey.key, 32));

	UInt256 otherPublicKey;
	net::read(socket.next_layer(), net::buffer(otherPublicKey.key, 32));
	
	UInt256 secret = ScalarMult(privateKey, otherPublicKey);
	memcpy(secret_, secret.key, 32);
	cout << "Secret:\t" << (string)secret << endl;
	socket.binary(true);
	socket.handshake(host_, handshake_);
	on_read();
}
void Client::on_read()
{
	socket.async_read(
		buffer_,
		[self = shared_from_this()](beast::error_code ec, std::size_t bytes)
		{

			if (!ec) {
				auto data = self->buffer_.data();
				std::vector<uint8_t> bytes(
					static_cast<const uint8_t*>(data.data()),
					static_cast<const uint8_t*>(data.data()) + data.size()
				);
				vector<uint8_t> rawBytes = self->decrypt(bytes);
				string text = string(rawBytes.begin(), rawBytes.end());
				cout << text << endl;
				self->buffer_.consume(self->buffer_.size());
				self->on_read();     // автоматически перезапускаем
			}
			else {
				self->fail(ec, "read");
			}
		});
}
void Client::send(const string& message) {
	const uint8_t* messageBytes = (const uint8_t*)message.data();
	size_t messageLen= message.size();
	vector<uint8_t> rawBytes = encrypt(messageBytes, messageLen);

	net::post(socket.get_executor(),
		[self = shared_from_this(), rawBytes]()
		{
			self->writeQueue.push(rawBytes);
			if (!self->isWriting)
				self->do_send();
		});
}
void Client::do_send() {
	if (writeQueue.empty()) {
		isWriting = false;
		return;
	}
	isWriting = true;
	socket.async_write(
		net::buffer(writeQueue.front()),
		beast::bind_front_handler(
			&Client::on_send,
			shared_from_this()));
}
void Client::on_send(beast::error_code ec, std::size_t) {
	if (ec) return fail(ec, "write");
	writeQueue.pop();   // удаляем отправленное
	do_send();          // отправляем следующее
}
void Client::fail(beast::error_code ec, const char* what)
{
	std::cout << what << ": " << ec.message() << std::endl;
	std::cout << what << ": " << ec.value() << std::endl;
}
vector<uint8_t> Client::encrypt(const uint8_t* plaintext, size_t plaintext_len) {
	uint8_t iv[12];
	RAND_bytes(iv, sizeof(iv));

	EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
	EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, secret_, iv);

	std::vector<uint8_t> ciphertext(plaintext_len);
	int len = 0;
	EVP_EncryptUpdate(ctx, ciphertext.data(), &len, plaintext, plaintext_len);

	int final_len = 0;
	EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &final_len);

	uint8_t tag[16];
	EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, 16, tag);

	EVP_CIPHER_CTX_free(ctx);

	std::vector<uint8_t> message;
	message.reserve(12 + ciphertext.size() + 16);
	message.insert(message.end(), iv, iv + sizeof(iv));
	message.insert(message.end(), ciphertext.begin(), ciphertext.end());
	message.insert(message.end(), tag, tag + sizeof(tag));

	return message;
}
vector<uint8_t> Client::decrypt(const std::vector<uint8_t>& message) {
	const uint8_t* iv = message.data();
	const uint8_t* ciphertext = message.data() + 12;
	size_t ciphertext_len = message.size() - 12 - 16;
	const uint8_t* tag = message.data() + message.size() - 16;

	EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
	EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, secret_, iv);
	std::vector<uint8_t> plaintext(ciphertext_len);
	int len = 0;
	EVP_DecryptUpdate(ctx, plaintext.data(), &len, ciphertext, ciphertext_len);
	// устанавливаем тег для проверки целостности
	EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, 16, (void*)tag);

	// завершаем — если тег не совпал вернёт <= 0
	int final_len = 0;
	int ret = EVP_DecryptFinal_ex(ctx, plaintext.data() + len, &final_len);
	return plaintext;
}