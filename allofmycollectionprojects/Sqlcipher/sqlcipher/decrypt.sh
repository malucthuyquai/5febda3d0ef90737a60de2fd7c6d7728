#!/bin/bash

echo 'Clean old file...'

rm -rf plaintext.db

echo 'Start decrypting file ' $1 '...'

./sqlite3 -batch $1 <<"EOF"

pragma key = '21fc123678edfd999aaab4f378b9110d';

attach database 'plaintext.db' as plaintext key '';

select sqlcipher_export('plaintext');

detach database plaintext;

.exit

EOF

echo done!

