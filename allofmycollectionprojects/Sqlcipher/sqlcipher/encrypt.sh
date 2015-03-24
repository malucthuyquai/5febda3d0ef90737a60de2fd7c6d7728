#!/bin/bash

echo 'Clean old file...'

rm -rf encrypted.db

echo 'Start encrypting file ' $1 '...'

./sqlite3 -batch $1 <<"EOF"

attach database 'encrypted.db' as encrypted key '21fc123678edfd999aaab4f378b9110d';

select sqlcipher_export('encrypted');

detach database encrypted;

.exit

EOF

echo done!

