#!/bin/bash
# Ova skripta je napravljena za Debian 13 verziju.
# Pokreće se sa: sudo bash setup.sh

# Provera privilegija
if [[ $EUID -ne 0 ]]; then
   echo "Pokreni skriptu kao root (sudo)." 
   exit 1
fi

# Početak aplikacije

echo "==== Ažuriranje paketa ===="
apt update && apt -y upgrade && apt -y dist-upgrade

echo "==== Dodavanje repozitorijuma (contrib i non-free) ===="
sed -i 's/main/main contrib non-free non-free-firmware/g' /etc/apt/sources.list

apt update

echo "==== Instalacija osnovnih paketa ===="
apt install -y sudo curl wget git neofetch htop build-essential software-properties-common

echo "==== Instalacija KDE Plasma ===="
apt install -y kde-plasma-desktop sddm kde-standard kde-spectacle konsole dolphin okular
apt install -y task-kde-desktop

echo "==== Postavljanje SDDM kao podrazumevanog display managera ===="
dpkg-reconfigure sddm

echo "==== Čišćenje sistema ===="
apt -y autoremove
apt -y autoclean

echo "==== GOTOVO! Restartuj računar za ulazak u KDE Plasma. ===="
