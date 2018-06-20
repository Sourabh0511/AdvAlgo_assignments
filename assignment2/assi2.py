from operator import eq
import pickle

class Suffix_Tree:



    
    def __init__(self):
        self.root = node()



    def build(self,title,s): # passing a dictionary which has title and string
        
        
        s = s + "$" #concatenating the terminal symbol
        for i in range(len(s)):
            c = node()
            c.set_suffix_num(title,i)
            if(self.root.is_leaf()):
                self.root.create_branch(s[i:],c)
            #else:
                '''if(self.root.branch[ord(s[i])] == {}):
                    self.root.create_branch(s[i:],c) '''   #not required to do this

            else:  
                    
                p = self.root #capture access point which is root
                k = i #capture the current index
                
                s_branches = p.get_all_children()
                while((p.is_leaf() == False) and (s_branches[ord(s[k])])):
                    # start matching and reach an internal node
                    label = list(s_branches[ord(s[k])].keys())[0] #edge string accesing
                    match = self.chars_matched(s[k:], label)

                    if(match == len(label)):
                                                            # root branch to point to an internal node
                        p = s_branches[ord(s[k])][label]
                        s_branches = p.get_all_children()

                        # while going if ended up in leaf node
                        if(p.is_leaf()):
                                                            # Merge initial and temp
                            p.set_suffix_num(title,i)

                    else:
                                                            # split the current node to add  the new node created
                        pre = s_branches[ord(s[k])].popitem() #to delete if key already exits using pop item
                        curr_label = pre[0]
                        curr_node = pre[1]

                        i_n = node()
                        # connect curr_node to i_n
                        i_n.create_branch(curr_label[match:], curr_node)

                        # attach i_n to starting 
                        p.create_branch(curr_label[0: match], i_n)
                        p = i_n
                        s_branches = p.get_all_children()
                    k = k + match

                # add the brannch and connect present and start
                if(p.is_leaf() == False):
                    p.create_branch(s[k:],c) 

            #print(self.root.get_all_children())
    def patt_match(self,pat):
    	
    	start = self.root
    	i = 0
    	while(i<len(pat) and mismatch == False):
    		st = start.branch[ord(pat[i])].keys()[0]
    		

    
                                    
    """
    def chars_matched(self,a,b):
        sli = list(map(eq,a,b)).index(False) doesnt work for few cases
        return sli """
    
    def chars_matched(self, a, b):
        i = 0
        while((i < len(a) and i < len(b)) and (a[i] == b[i])):
            i += 1
        return i

    """def patt_match(self,pat):
    	start = self.root
    	i = 0
    	mismatch = False
    	while(i<len(pat) and mismatch == False):"""



class node:
    
        def __init__(self):
        
            self.ind_n = {} #suffix number to be used in set suff number
            self.branch = [{}]*256
            #self.branches = {} # contains references of all the children nodes in the list
            #tale tile we can make it key in dictionary
    
        def set_suffix_num(self,tit,n): #index at which suffix string starts
            self.ind_n[tit] = n

        def create_branch(self,subs,child):
            temp = {}  #because it creates duplicates in each and every dictionary
            temp[subs] = child
            self.branch[ord(subs[0])] = temp
            
        def get_suffix_num(self):
            return self.ind_n
        def get_all_children(self):
            return self.branch
        
        def get_leaves(self): #returns a list of nodes iteraing through the branches a recursive call
        	if(self.is_leaf()):
        		return [self]
        	else:
        		lis = []
        		for i in self.branch:
        			if(i != {}):
        				lis.append(list(i.values())[0])

        		return [x for n in lis for x in n.get_leaves()]


        def is_leaf(self):
            if(self.branch == [{}]*256):
                return True
            else:
                return False





        #t = self.root.get_all_children()
        #print(t)
            

'''    
tree = Suffix_Tree()
di = {"A":"""A CONTROVERSY prevailed among the beasts of the field as to which of the animals deserved the most credit for producing the greatest number of whelps at a birth.  They rushed clamorously into the presence of the Lioness and demanded of her the settlement of the dispute. "And you," they said, "how many sons have you at a birth?'The Lioness laughed at them, and said: "Why! I have only one; but that one is altogether a thoroughbred Lion." The value is in the worth, not in the number."""}
di2 = {"A":"apple"}
di3 = {"B":"maple"} 
test = {"title":"amx"}
test1 = {"tale1":"""WOLF, meeting with a Lamb astray from the fold, resolved not to lay violent hands on him, but to find some plea to justify to the Lamb the Wolf's right to eat him.  He thus addressed him: "Sirrah, last year you grossly insulted me."  "Indeed," bleated the Lamb in a mournful tone of voice, "I was not then born."  Then said the Wolf, "You feed in my pasture."  "No, good sir," replied the Lamb, "I have not yet tasted grass."  Again said the Wolf, "You drink of my well."  "No," exclaimed the Lamb, "I never yet drank water, for as yet my mother's milk is both food and drink to me."  Upon which the Wolf seized him and ate him up, saying,"Well! I won't remain supperless, even though you refute every one of my imputations."  The tyrant will always find a pretext for his tyranny."""}
tree.build(di) '''
tree = Suffix_Tree()
with open('processed_dataset.pickle', 'rb') as handle:
    diction = pickle.load(handle)

for keys in diction :
	tree.build(keys,diction[keys])
#tree.build(di2)
#tree.build(di3)
#tree.build(di2)



"""p_s = list(self.root.branch[ord(s[i])].keys())[0]   alternative method which doesnt work
                    c_s = s[i:]
                    sli = list(map(eq,p_s,c_s)).index(False) #find the mismatch point
                    matched = p_s[:sli] #get the matched portion
                    p_s1 = p_s[sli:] 
                    c_s1 = c_s[sli:]
                    t = node() #internal node to attach unmatched branches 
                    l1 = node() #node for parent split
                    l2 = node() #node for child split
                    l1 = list(self.root.branch[ord(s[i])].values())[0] #access the value node of the key of parent and set it to the new node
                    l2.set_suffix_num(title,i)
                    temp = {} #assign this temp dict to self.root.branch[ord(s[i])]
                    t.create_branch(p_s1,l1)
                    t.create_branch(c_s1,l2) #add the two unmatched substrings as branches to this t node 
                    temp[matched] = t
                    self.root.branch[ord(s[i])] = temp #replace the original dictionary at that index with temp
                    """
#dic.keys = [x:x in [chr(i) for i in range(127)]] might be useful