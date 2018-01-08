#!/bin/sh
set -ex
hhvm --version
echo hhvm.jit=0 >> /etc/hhvm/php.ini
curl https://getcomposer.org/installer | hhvm -d hhvm.jit=0 --php -- /dev/stdin --install-dir=/usr/local/bin --filename=composer

cd /var/source
hhvm /usr/local/bin/composer install

hh_server --check $(pwd)
hhvm -d hhvm.php7.all=0 vendor/bin/phpunit
hhvm -d hhvm.php7.all=1 vendor/bin/phpunit

sed -i '/enable_experimental_tc_features/d' .hhconfig
hh_server --check $(pwd)
