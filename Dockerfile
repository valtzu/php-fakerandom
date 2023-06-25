FROM php:8.2-cli

COPY . /php-fakerandom
WORKDIR /php-fakerandom
RUN phpize
RUN php build/gen_stub.php && ./configure && make && make install

CMD ["make", "test", "REPORT_EXIT_STATUS=1", "NO_INTERACTION=1", "TESTS=--show-all"]
