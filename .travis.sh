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
composer install

hh_client
vendor/bin/hacktest tests/

if [ "$(hhvm --php -r 'var_dump(HHVM_VERSION_ID >= 44600);')" = "bool(true)" ]; then
  hh_client stop
  echo disable_xhp_element_mangling=true >> .hhconfig
  echo enable_xhp_class_modifier=true >> .hhconfig
  hh_client
  rm -f ~/.hhvm.hhbc
  hhvm -dhhvm.hack.lang.disable_xhp_element_mangling=true -dhhvm.hack.lang.enable_xhp_class_modifier=true vendor/bin/hh-autoload
  hhvm -dhhvm.hack.lang.disable_xhp_element_mangling=true -dhhvm.hack.lang.enable_xhp_class_modifier=true vendor/bin/hacktest tests/
fi
