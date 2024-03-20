# note in nested loops
for i in range(1,10):
    print("---Beginning of second loop---") 
    for j in range(1,10):
        print("i=",i,"  j=",j)
    print("---End of second loop---\n\n\n") 


'''
1
1 2
1 2 3
1 2 3 4
'''

# eg 1
for i in range(1,5):
    for j in range(1,  i+1 ):
        print(j,end=" ")
    print()


# eg 2
for i in range(6):
    for j in range(i):
        print(j+1  ,end=" ")
    if i == 0:
        pass
    else:
        print()

# eg 3
for i in range(6):
    for j in range(i):
        print(j+1  ,end=" ")
    if i != 0:
        print()

for  i in range(10):
    print("Hi")

# ------------------------------ END OF normal triangle --------------------------------

'''
1 2 3 4
1 2 3
1 2
1
'''

# eg 4
a = 6
for i in range(1,5):
    for j in range(1,a-1):
        print(j,end=" ")
    print()
    a-=1
    
    

# eg 5 (Negative indexing)
for i in range(5,1,-1):
    for j in range(1,i):
        print(j,end=" ")
    print()
    
    
# eg 6  ( relation between i and j )
for i in range(1,5):
    # as i increases, the range of j needs to decrese
    for j in range(1,  5-i+1 ):
        print(j,end=" ")
    print()
    
    
# ---------------------------------------------------------------------------------- 
    
'''
1
1 2
1 2 3
1 2
1
'''

# Most complicated code by Achu
for i in range(1,4):
    for j in range(1,i+1):
        print(j,end=" ")
    print()
a = 4
for i in range(1,3):
    for j in range(1,a-1): 
        print(j,end=" ")
    print()
    a-=1
    
    
# -------------------------------------------------------------------------

'''
1 2 3
1 2
1 
1 2
1 2 3
1 2 3 4 
1 2 3 4 5
'''

'''
1 2 3
1 2
1
'''
a = 5 
for i in range(1,4):
    for j in range(1,a-1):
        print(j,end=" ")
    print()
    a-=1
    

'''
1 2
1 2 3
1 2 3 4 
1 2 3 4 5
'''
for i in range(1,  5 ):
    for j in range(1,  i + 2 ):
        print(j,end=" ")
    print()
    

# Another methode
'''
1 2
1 2 3
1 2 3 4 
1 2 3 4 5
'''
for i in range(1,5):
    if i!=1 :
        for j in range(1,  i+1 ):
            print(j,end=" ")
    if i!=1 :
        print()
        
        
