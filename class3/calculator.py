def readNumber(line, index):
    number = 0
    flag = 0
    keta = 1
    while index < len(line) and (line[index].isdigit() or line[index] == '.'):
        if line[index] == '.':
            flag = 1
        else:
            number = number * 10 + int(line[index])
            if flag == 1:
                keta *= 0.1
        index += 1
    token = {'type': 'NUMBER', 'number': number * keta}
    return token, index


def readPlus(line, index):
    token = {'type': 'PLUS'}
    return token, index + 1


def readMinus(line, index):
    token = {'type': 'MINUS'}
    return token, index + 1


def readMaltiply(line, index):
    token = {'type': 'MALTIPLY'}
    return token, index + 1


def readDivid(line, index):
    token = {'type': 'DIVID'}
    return token, index + 1

def readLeft(line, index):
    token = {'type': 'LEFT'}
    return token, index + 1

def readRight(line, index):
    token = {'type': 'RIGHT'}
    return token, index + 1


def tokenize(line):
    tokens = []
    index = 0
    while index < len(line):
        if line[index].isdigit():
            (token, index) = readNumber(line, index)
        elif line[index] == '+':
            (token, index) = readPlus(line, index)
        elif line[index] == '-':
            (token, index) = readMinus(line, index)
        elif line[index] == '*':
            (token, index) = readMaltiply(line, index)
        elif line[index] == '/':
            (token, index) = readDivid(line, index)
        elif line[index] == '(':
            (token, index) = readLeft(line, index)
        elif line[index] == ')':
            (token, index) = readRight(line, index)
        else:
            print 'Invalid character found: ' + line[index]
            exit(1)
        tokens.append(token)
    return tokens


def evaluate(tokens):
    tokens=evaluate_parenthese(tokens)
    tokens=evaluate_mal_div(tokens)
    answer=evaluate_plus_minus(tokens)
    return answer

def evaluate_parenthese(tokens):
    index=1
    while index < len(tokens):
        if tokens[index]['type'] == 'RIGHT':
            tmp=[]
            tokens.pop(index)
            index-=1
            while tokens[index]['type'] != 'LEFT' :
                tmp.append(tokens[index])
                tokens.pop(index) #pop number
                index-=1
            tokens.pop(index) #pop left parenthese 
            #print "tmp" ,tmp
            tmp_token=evaluate_mal_div(tmp)
            tmp_ans=evaluate_plus_minus(tmp_token)
            #print "ans",tmp_ans,"index",index
            tokens.insert(index, {'type': 'NUMBER', 'number': tmp_ans} )
            #print tokens
            
        index+=1
    return tokens

def evaluate_mal_div(tokens):
    tmp = [1]
    tokens.insert(0, {'type': 'PLUS'}) # Insert a dummy '+' token
    index = 1
        
    while index < len(tokens):
        if tokens[index]['type'] == 'NUMBER':
            if tokens[index - 1]['type'] == 'MALTIPLY':
                tmp = tokens[index-2]['number']*tokens[index]['number']
                #print tmp # test
                tokens[index]['number']=tmp  
                #print tokens # test      
                tokens.pop(index-1)
                index-=1
                tokens.pop(index-1)

            elif tokens[index - 1]['type'] == 'DIVID':
                tmp = tokens[index-2]['number']/tokens[index]['number']
                tokens[index-2]['number']=tmp
                tokens[index]['number']=tmp  
                tokens.pop(index-1)
                index-=1
                tokens.pop(index-1)

        index+=1

    return tokens

def evaluate_plus_minus(tokens):
    answer = 0
    index = 1
    while index < len(tokens):
        if tokens[index]['type'] == 'NUMBER':
            if tokens[index - 1]['type'] == 'PLUS':
                answer += tokens[index]['number']
            elif tokens[index - 1]['type'] == 'MINUS':
                answer -= tokens[index]['number']
            else:
                print 'Invalid syntax'
        index+=1

    return answer


#test function
def test(line, expectedAnswer):
    tokens = tokenize(line)
    actualAnswer = evaluate(tokens)
    if abs(actualAnswer - expectedAnswer) < 1e-8:
        print "PASS! (%s = %f)" % (line, expectedAnswer)
    else:
        print "FAIL! (%s should be %f but was %f)" % (line, expectedAnswer, actualAnswer)


# Add more tests to this function :)
def runTest():
    print "==== Test started! ===="
    test("1+2", 3)
    test("3*2", 6)
    test("3*2*5", 30)
    test("3*2*5*2*2*2/4", 60)
    test("(1+2)*2", 6)
    test("((1+2)*5)*2", 30)
    test("((1+2)*5)*2+(3+4)*2", 44)
    print "==== Test finished! ====\n"

runTest()

while True:
    print '> ',
    line = raw_input()
    tokens = tokenize(line)
    answer = evaluate(tokens)
    print "answer = %f\n" % answer