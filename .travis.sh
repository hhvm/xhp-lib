#!/bin/sh
set -ex
hhvm --version
apt-get update -y
apt-get install -y wget curl git
curl https://getcomposer.org/installer | hhvm -d hhvm.jit=0 --php -- /dev/stdin --install-dir=/usr/local/bin --filename=composer

cd /var/source
hhvm -d hhvm.jit=0 /usr/local/bin/composer install
hhvm -d hhvm.jit=0 vendor/bin/phpunit tests/
