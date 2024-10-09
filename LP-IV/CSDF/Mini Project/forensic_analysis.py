# 41429 
# Vedant Kokane


import email
import pyshark

# 1. Email Forensics: Simple header analysis
def analyze_email_headers(email_file):
    try:
        with open(email_file, 'r') as f:
            msg = email.message_from_file(f)
            print(f"From: {msg['From']}")
            print(f"To: {msg['To']}")
            print(f"Subject: {msg['Subject']}")
            print(f"Date: {msg['Date']}")
    except Exception as e:
        print(f"Error in email forensics: {e}")

# 2. Network Forensics: Analyze network traffic using pyshark
def analyze_network_traffic(pcap_file):
    try:
        cap = pyshark.FileCapture(pcap_file)
        for packet in cap:
            print(f"Packet: {packet}")
            if packet.ip:
                print(f"Source: {packet.ip.src}, Destination: {packet.ip.dst}")
    except Exception as e:
        print(f"Error in network forensics: {e}")

# 3. Memory Forensics: Placeholder (Basic mockup)
def analyze_memory_dump(memory_file):
    try:
        print(f"Analyzing memory dump: {memory_file}")
        # Here, a real memory dump analysis would take place using Volatility, Rekall, etc.
        print("[Mockup] Detected suspicious processes from memory dump.")
    except Exception as e:
        print(f"Error in memory forensics: {e}")
