FROM php:8.1-cli

COPY ./src /src/php-fakerandom
WORKDIR /src/php-fakerandom
RUN phpize
RUN php build/gen_stub.php && ./configure && make && make install

CMD ["make", "test", "REPORT_EXIT_STATUS=1", "NO_INTERACTION=1", "TESTS=--show-all"]
