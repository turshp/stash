import urllib
import re

sock = urllib.urlopen('http://www.qq.com')
htmlfile = sock.read()

print 'Open tags:'
print re.findall(r'<[^/>][^>]*[^/>]>', htmlfile) [0:3]
print 'Close tags:'
print re.findall(r'</[^>/]+>', htmlfile) [0:3]
print 'Self-close tags:'
print re.findall(r'<[^/>]+/>', htmlfile) [0:3]

