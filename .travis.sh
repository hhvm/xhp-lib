#!/bin/bash
set -ex
apt update -y
DEBIAN_FRONTEND=noninteractive apt install -y php-cli zip unzip
hhvm --version
php --version

(
  cd $(mktemp -d)
  curl https://getcomposer.org/installer | php -- --install-dir=/usr/local/bin --filename=composer
)
composer install || true

hhvm -dhhvm.hack.lang.enable_xhp_class_modifier=true -dhhvm.hack.lang.disable_xhp_element_mangling=true vendor/bin/hh-autoload
hh_client
hhvm -dhhvm.hack.lang.enable_xhp_class_modifier=true -dhhvm.hack.lang.disable_xhp_element_mangling=true vendor/bin/hacktest tests/
hhvm -dhhvm.hack.lang.enable_xhp_class_modifier=true -dhhvm.hack.lang.disable_xhp_element_mangling=true vendor/bin/hhast-lint
