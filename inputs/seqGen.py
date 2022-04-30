import random
n=25
m=25
while(n<=250):
     while(m<=250):
        file = f"{n:03d}n{m:03d}m.seq"
        f = open(file, 'w')
        seq=[str(n)+'\n',
            str(m)+'\n',
            ''.join(random.choices(['A','T','C','G','-'],k=n))+'\n',
            ''.join(random.choices(['A','T','C','G','-'],k=m))]
        f.writelines(seq)
        f.close()
        m+=25
     m=25
     n+=25