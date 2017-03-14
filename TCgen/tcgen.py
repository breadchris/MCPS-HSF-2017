# empty truecrypt volume generator
# @author: anonyn00se
# @website: operati0ns.pythonanywhere.com

import subprocess
import random
import sys

if len(sys.argv) < 2:
    print 'Usage: python tcgen.py [amount]'
    quit()

n = int(sys.argv[1])

# read in passwords
passwords = []
with open('/usr/share/dict/words') as f:
    for word in f:
        passwords.append(word.strip().lower().replace('\'', ''))
        

cmd = 'truecrypt -t -c %s.tc --password=%s --non-interactive --encryption=AES ' + \
'--hash=SHA-512 --filesystem=FAT --size=%d --random-source=/dev/urandom ' + \
'--volume-type=normal'

for i in range(n):
    password = random.choice(passwords)
    size = random.randrange(20 * 10**6, 50 * 10**6)
    name = '%08d' % random.randrange(0, 10**8)
    subprocess.call(cmd % (name, password, size), shell=True)
    print '%s.tc created with password %s' % (name, password)

