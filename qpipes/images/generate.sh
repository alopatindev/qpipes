#!/bin/bash

RESOURCES=resources.qrc
LEVEL="10%,75%"

echo 'generating images...'

convert 00010.png -level $LEVEL 00011.png
convert 00010.png -rotate 180 00100.png
convert 00010.png -rotate 180 -level $LEVEL 00101.png
#convert 00010.png -rotate -90 01000.png
#convert 00010.png -rotate -90 -level $LEVEL 01001.png
#convert 00010.png -rotate 90 10000.png
#convert 00010.png -rotate 90 -level $LEVEL 10001.png

convert 00110.png -level $LEVEL 00111.png
convert 00110.png -rotate 90 11000.png
convert 00110.png -rotate 90 -level $LEVEL 11001.png

convert 01010.png -level $LEVEL 01011.png
convert 01010.png -rotate -90 01100.png
convert 01010.png -rotate -90 -level $LEVEL 01101.png
convert 01010.png -rotate 90 10010.png
convert 01010.png -rotate 90 -level $LEVEL 10011.png
convert 01010.png -rotate -180 10100.png
convert 01010.png -rotate -180 -level $LEVEL 10101.png

echo 'generating resource file...'

echo '<RCC>
  <qresource>' > ${RESOURCES}

for i in *.png; do
    echo "    <file>${i}</file>" >> ${RESOURCES}
done

echo '  </qresource>
</RCC>' >> ${RESOURCES}
