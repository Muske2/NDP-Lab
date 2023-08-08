sentence=input('Enter sentence: ')
words=sentence.split()
k=0
count=0
di={}
for i in words:
    di[k]=i
    k+=1
    count+=1
print ('Number of words: ',count,'\n',di)
