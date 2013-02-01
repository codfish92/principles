(require racket/trace) ; used for (trace funcName)
(define aSampleList (list 'a 'b 'c 'd)); a test list
(define anotherSampleList (list 'b 'c (list 'a 'b 'c))) ; a more complicated test list using a list inside of a list
(define (containsAnywhere element aList) ; given an element and a valid list
  (if (member element aList) #t #f)) ; uses builtin member function on lists which returns the list if the given element is a member of the list and a #f otherwise

