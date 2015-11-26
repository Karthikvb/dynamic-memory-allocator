
def getModulo3(str, l, r):
	return int(str[l:r+1], 2)
	
str_len = int(raw_input())
print str_len
print "\n"
string = raw_input()
print string
print "\n"
ntc = int(raw_input())
print ntc
print "\n"

for i in range(1, ntc+1):
	query = split(raw_input())
	print query
	print "\n"
	if query[0] == 0:
		print getModulo3(string, query[1], query[2])
		print "\n"
