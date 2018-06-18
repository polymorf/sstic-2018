from polytools import *
from r4aes import AES_128
import struct
import sys

"""
00000000 message_header  struc ; (sizeof=0x28, mappedto_48)
00000000                                         ; XREF: message/r
00000000 magic1          db 8 dup(?)             ; XREF: mesh_process_message+45/r
00000000                                         ; mesh_process_message+196/w
00000008 seed_agent_name db 8 dup(?)
00000010 agent_id        dq ?                    ; XREF: mesh_agent_peering+3D/w
00000010                                         ; mesh_agent_peering+D7/r ...
00000018 gateway_id      dq ?                    ; XREF: mesh_agent_peering+34/w
00000018                                         ; mesh_process_message+CE/r
00000020 command         dd ?                    ; XREF: mesh_agent_peering+4C/w
00000020                                         ; mesh_agent_peering+87/r ...
00000024 size_maybe      dd ?                    ; XREF: mesh_agent_peering+8E/r
00000024                                         ; mesh_agent_peering+B1/r ...
00000028 message_header  ends
"""

def parse_ct(data):
	magic1,data = data[:8],data[8:]
	agent_name,data = data[:8],data[8:]
	agent_id,data = data[:8],data[8:]
	gateway_id,data = data[:8],data[8:]
	command,data = struct.unpack("<I",data[:4])[0],data[4:]
	size,data = struct.unpack("<I",data[:4])[0],data[4:]

	print "magic       : %s" % magic1.encode("hex")
	print "agent_name  : %s" % agent_name
	print "agent_id    : %s" % agent_id.encode("hex")
	print "gateway_id  : %s" % gateway_id.encode("hex")
	print "command     : 0x%08x" % command
	print "size        : 0x%08x" % (size - 0x28)

	data = data[8:]

	family,data = struct.unpack("<H",data[:2])[0],data[2:]
	port,data = struct.unpack(">H",data[:2])[0],data[2:]
	ip,data = data[:4],data[4:]
	pad,data = data[:8],data[8:]
	print "family        : 0x%02x" % (family)
	print "port          : %d" % (port)
	print "ip            : %d.%d.%d.%d" % (ord(ip[0]), ord(ip[1]), ord(ip[2]), ord(ip[3]))

	decRk,data = data[:0xf0],data[0xf0:]
	hexdump(decRk[:0x40], title="decRk")
	encRk,data = data[:0xf0],data[0xf0:]
	hexdump(encRk[:0x40], title="encRk")
	
	decKey,data = data[:0x10],data[0x10:]
	hexdump(decKey, title="decKey")
	encKey,data = data[:0x10],data[0x10:]
	hexdump(encKey, title="encKey")
	
	field_200,data = data[:8],data[8:]
	field_208,data = data[:8],data[8:]
	fd,data = data[:4],data[4:]
	hexdump(data)




sens = ""
if len(sys.argv) == 2:
	sens = sys.argv[1]
if sens not in ("client", "server"):
	print "usage: client ou server"
	sys.exit(0)

data = ""
key = ""
if sens == "server":
	print "serveur"
	data = open("../1/flux/192.168.023.213.31337-192.168.231.123.49734","rb").read()
	key = "".join(map(chr,[76, 26, 105, 54, 47, 224, 3, 54, 246, 168, 70, 15, 243, 61, 255, 213])) # server
else:
	print "client"
	data = open("../1/flux/192.168.231.123.49734-192.168.023.213.31337","rb").read()
	key = "".join(map(chr,[114, 255, 128, 54, 217, 32, 7, 119, 209, 233, 122, 91, 225, 211, 245, 20])) # client

data = data[0x200:]

# python2 parse.py  |sort|uniq |grep 00000000000000000000000000000000 -A 255 |awk '{print $NF}' > ciphertext_server.txt



crypt = AES_128()
crypt.key = key

a = open("echanges_%s.bin" % sens, "wb")

k=0
while len(data):
	k+=1
	(read_len,data) = (struct.unpack("<I",data[:4])[0],data[4:])
	if len(data) <= 4:
		break
	bloc,data = data[:read_len],data[read_len:]
	#hexdump(bloc[0x0:0x20])
	#break
	#if read_len == 16336:
	iv = bloc[:0x10]
	ciphertext = bloc[0x10:]
	cleartext=""
	# if len(bloc) < 200:
	# 	continue
	for i in range(0,len(ciphertext),16):
		b = ciphertext[i:i+16]
		if len(b) != 16:
			error("BAD LEN")
			hexdump(bloc)
		cleartext += xor(crypt.inv_cipher(b), iv)
		iv = b

	pkt_type = cleartext[0x20:0x28]
	if pkt_type.startswith("\x01\x02\x00\x03"):
		info(">>>> stdout <<<<")
		print cleartext[0x28:].replace("\x00","")
	elif pkt_type.startswith("\x04\x02\x00\x03") or pkt_type.startswith("\x02\x02\x00\x03"):
		# file
		a.write(cleartext[0x28:])
	elif pkt_type.startswith("\x01\x02\x00\x05"):
		info("cmd ack")
		#hexdump(cleartext[0x28:0x100])
	elif pkt_type.startswith("\x01\x02\x00\x00"):
		info("cmd : %s" % cleartext[0x28:].replace("\x00",""))
	elif pkt_type.startswith("\x04\x02\x00\x00"):
		info("get file : %s" % cleartext[0x28:].replace("\x00",""))
	elif pkt_type.startswith("\x02\x02\x00\x00"):
		info("push file : %s" % cleartext[0x28:].replace("\x00",""))
	elif pkt_type.startswith("\x04\x02\x00\x05") or pkt_type.startswith("\x02\x02\x00\x05"):
		info("END SESSION")
	elif pkt_type.startswith("\x00\x00\x01\x01"):
		# TODO
		hexdump(cleartext, title="todo")
		parse_ct(cleartext)
		#break

	else:
		#hexdump(pkt_type)
		#hexdump(cleartext[0x28:0x100])
		pass



