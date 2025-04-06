# 41429 
# Vedant Kokane

import forensic_analysis as fa

def menu():
    print("\nCyber-Crime Analysis System")
    print("1. Email Forensics")
    print("2. Network Forensics")
    print("3. Memory Forensics")
    print("4. Exit")
    return int(input("Select an option: "))

if __name__ == "__main__":
    while True:
        choice = menu()

        if choice == 1:
            email_file = "sample_data/sample_email.eml"
            print("\n[Performing Email Forensics]\n")
            fa.analyze_email_headers(email_file)

        elif choice == 2:
            pcap_file = "sample_data/sample_network.pcap"
            print("\n[Performing Network Forensics]\n")
            fa.analyze_network_traffic(pcap_file)

        elif choice == 3:
            memory_file = "sample_data/sample_memory.img"
            print("\n[Performing Memory Forensics]\n")
            fa.analyze_memory_dump(memory_file)

        elif choice == 4:
            print("Exiting system.")
            break

        else:
            print("Invalid choice, try again.")
