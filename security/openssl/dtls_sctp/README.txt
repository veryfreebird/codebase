sudo modprobe sctp
sudo sysctl -w net.sctp.auth_enable=1

server: ~/my-openssl/bin/openssl s_server -accept 2000 -dtls -sctp -key server-key.pem -cert server-cert.pem

client: ~/my-openssl/bin/openssl s_client -connect 127.0.0.1:2000 -dtls -sctp -keylogfile keys.log

