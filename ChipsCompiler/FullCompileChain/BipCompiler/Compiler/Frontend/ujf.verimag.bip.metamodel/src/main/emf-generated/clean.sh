HANDMODIFIED=$(rgrep 'generated NOT' bip2/*| cut -d':' -f1 | sort -u)

mkdir HM-backup

for f in $HANDMODIFIED; do
     mkdir -p HM-backup/$(dirname $f)
     cp $f HM-backup/$(dirname $f)
done

 rm -rf bip2

 mv HM-backup/bip2 bip2
 rmdir HM-backup

