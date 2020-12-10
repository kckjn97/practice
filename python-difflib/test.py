text1 = """Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Integer
eu lacus accumsan arcu fermentum euismod. Donec pulvinar porttitor
tellus. Aliquam venenatis. Donec facilisis pharetra tortor.  In nec
mauris eget magna consequat convallis. Nam sed sem vitae odio
pellentesque interdum. Sed consequat viverra nisl. Suspendisse arcu
metus, blandit quis, rhoncus ac, pharetra eget, velit. Mauris
urna. Morbi nonummy molestie orci. Praesent nisi elit, fringilla ac,
suscipit non, tristique vel, mauris. Curabitur vel lorem id nisl porta
adipiscing. Suspendisse eu lectus. In nunc. Duis vulputate tristique
enim. Donec quis lectus a justo imperdiet tempus."""
text1_lines = text1.splitlines()

text2 = """Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Integer
eu lacus accumsan arcu fermentum euismod. Donec pulvinar, porttitor
tellus. Aliquam venenatis. Donec facilisis pharetra tortor. In nec
mauris eget magna consequat convallis. Nam cras vitae mi vitae odio
pellentesque interdum. Sed consequat viverra nisl. Suspendisse arcu
metus, blandit quis, rhoncus ac, pharetra eget, velit. Mauris
urna. Morbi nonummy molestie orci. Praesent nisi elit, fringilla ac,
suscipit non, tristique vel, mauris. Curabitur vel lorem id nisl porta
adipiscing. Duis vulputate tristique enim. Donec quis lectus a justo
imperdiet tempus. Suspendisse eu lectus. In nunc. """
text2_lines = text2.splitlines()

import difflib
from pprint import pprint

d = difflib.Differ()
diff = list(d.compare(text1, text2))
pprint(diff)

print('-----------------------------')
diff = list(d.compare(text1_lines, text2_lines))
pprint(diff)

print('-----------------------------')
text1_lines_with_number = []
text2_lines_with_number = []

for i in range(len(text1_lines)):
	text1_lines_with_number.append(str(i) + ': ' + text1_lines[i])

for i in range(len(text2_lines)):
	text2_lines_with_number.append(str(i) + ': ' + text2_lines[i])

diff = list(d.compare(text1_lines_with_number, text2_lines_with_number))
for l in diff:
	if l[0] == '+' or l[0] == '-':
		print(l)
