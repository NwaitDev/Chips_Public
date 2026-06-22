#!/bin/bash

if [ "$USER" != "async" ]; then
    echo "You should not run this script if not using the 'async' account"
    exit 255
fi

make html latexpdf && rsync -av ./build/html/ /import/www/TOOLS/DCS/bip/doc/latest/html/ && \
 mkdir -p /import/www/TOOLS/DCS/bip/doc/latest/pdf && \
 cp build/latex/BIP2.pdf /import/www/TOOLS/DCS/bip/doc/latest/pdf && \
 pdfbook build/latex/BIP2.pdf && mv BIP2-book.pdf  /import/www/TOOLS/DCS/bip/doc/latest/pdf/BIP2-minibook.pdf

mkdir -p /import/www/TOOLS/DCS/bip/doc/latest/examples/ && \
  rsync --delete \
        --exclude "*.o" --exclude "*build/" \
        --include "**/*.bip" --include "**/*.cpp" --include "**/*.hpp" --include "**/*.sh" \
        -avz tutorial_src/ \
        /import/www/TOOLS/DCS/bip/doc/latest/examples/

echo "Options +Indexes" > /import/www/TOOLS/DCS/bip/doc/latest/examples/.htaccess
