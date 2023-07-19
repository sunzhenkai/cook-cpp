#!/bin/bash
# check os information
if [ -f "/etc/os-release" ]; then
    . /etc/os-release
elif [ -f "/etc/arch-release" ]; then
    export ID=arch
else
    echo "/etc/os-release missing."
    exit 1
fi

# define packages for oses
debian_packages=(
    make
    cmake
    ninja-build
    xfslibs-dev
    systemtap-sdt-dev
    pkg-config
)

fedora_packages=(
)

# centos7 & centos8 common packages
redhat_packages=(
)

centos7_packages=(
    "${redhat_packages[@]}"
)

centos8_packages=(
    "${redhat_packages[@]}"
)

arch_packages=(
  make
  cmake
  pkg-config
)

opensuse_packages=(
)

case "$ID" in
ubuntu | debian | pop)
    apt-get install -y "${debian_packages[@]}"
    ;;
fedora)
    dnf install -y "${fedora_packages[@]}"
    ;;
rhel | centos | rocky)
    if [ "$VERSION_ID" = "7" ]; then
        yum install -y epel-release centos-release-scl scl-utils
        yum install -y "${centos7_packages[@]}"
    elif [ "${VERSION_ID%%.*}" = "8" ]; then
        dnf install -y epel-release
        dnf install -y "${centos8_packages[@]}"
    fi
    ;;
opensuse-leap)
    zypper install -y "${opensuse_packages[@]}"
    ;;
arch | manjaro)
    if [ "$EUID" -eq "0" ]; then
        pacman -Sy --needed --noconfirm "${arch_packages[@]}"
    else
        echo "running without root. Skipping main dependencies (pacman)." 1>&2
    fi
    ;;
*)
    echo "Your system ($ID) is not supported by this script. Please install dependencies manually."
    exit 1
    ;;
esac
