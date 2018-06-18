from scapy.all import *
from polytools import *
import gmpy
import struct
from Crypto.Cipher import AES
from r4aes import AES_128

pcap = rdpcap("../challenge_SSTIC_2018_31337.pcap")

f1 = open("ciphertext_client.txt","wb")
f2 = open("ciphertext_server.txt","wb")

client_iv = 0;
	
server_key = "".join(map(chr,[76, 26, 105, 54, 47, 224, 3, 54, 246, 168, 70, 15, 243, 61, 255, 213])) # server
client_key = "".join(map(chr,[114, 255, 128, 54, 217, 32, 7, 119, 209, 233, 122, 91, 225, 211, 245, 20])) # client

def decrypt(payload, crypt):
	iv = payload[:16]
	payload = payload[16:]
	message=""
	for i in range(0,len(payload),16):
		ciphertext_bloc = payload[i:i+16]
		if len(ciphertext_bloc) != 16:
			break
		dec_bloc   = xor(crypt.inv_cipher(ciphertext_bloc),iv)
		iv = ciphertext_bloc
		message +=  dec_bloc
	return message


def decrypt_server(payload):
	crypt = AES_128()
	crypt.key = server_key
	return decrypt(payload,crypt)
def decrypt_client(payload):
	crypt = AES_128()
	crypt.key = client_key
	return decrypt(payload,crypt)



i=0
for pkt in pcap:
	i+=1
	if i < 5:
		continue
	client=False
	if pkt[IP].src == "192.168.231.123":
		client=True
	data = pkt[TCP].load
	if client:
		if len(data) < 0x10:
			hexdump(data,"client", color=2)
		else:
			hexdump(decrypt_client(data),"client", color=2)

	else:
		if len(data) < 0x10:
			hexdump(data,"server", color=1)
		else:
			hexdump(decrypt_server(data),"server", color=1)

	
	