#!/bin/sh
set -ex
apt update -y
DEBIAN_FRONTEND=noninteractive apt install -y php-cli zip unzip
hhvm --version
php --version

(
  cd $(mktemp -d)
  curl https://getcomposer.org/installer | php -- --install-dir=/usr/local/bin --filename=composer
)
composer install --no-autoloader

hhvm \
  -dhhvm.hack.lang.enable_xhp_class_modifier=false \
  -dhhvm.hack.lang.disable_xhp_element_mangling=false \
  vendor/bin/hh-autoload

hh_client

hhvm \
  -dhhvm.hack.lang.enable_xhp_class_modifier=false \
  -dhhvm.hack.lang.disable_xhp_element_mangling=false \
  vendor/bin/hacktest tests/
