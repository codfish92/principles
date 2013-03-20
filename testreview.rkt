(define (oddElements aList)
  (if (empty? aList)
      (display "\n")
      (if (equal? (modulo (length aList) 2) 1)
                 (begin (display (car aList)) (display ", ") (oddElements (cdr aList)))
                 (oddElements (cdr aList))
                 )
                 );end if
  );

(define (evenElements aList)
  (if (empty? aList)
      (display "\n")
      (if (equal? (modulo (length aList) 2) 0)
                 (begin (display (car aList)) (display ", ") (evenElements (cdr aList)))
                 (evenElements (cdr aList))
                 )
                 );end if
  );

(cddar '((Alicia brenda charles)(100 main street)(golden co 80401)));remeber to read it right to left, so its car then cdr then cdr

(define (mergelists aList bList)
  (cond 
    [(empty? bList) 
     aList]
    [(empty? aList) 
     bList ]
    [(equal? (car aList)(car bList)) 
     (cons (car aList) (mergelists (cdr aList) bList))]
    [(> (car aList) (car bList)) 
     (cons (car bList) (mergelists aList (cdr bList)))]
    [(< (car aList) (car bList)) 
     (cons (car aList) (mergelists (cdr aList) bList))]
    
    )
  
  );end define
  
(define (cl x)
  (let* [ (y 5) (z 20) (fn (lambda (y) (* x y z))) ]
    (let [ (y 10) (z (+ x y z)) ]
      (fn z)
     )
   )
)

;(cl 5) outputs 3000 mainly because the second let is not a let*, so the z(+xyz) sees the y from the let* not the let
; final function ends up being (* 5 30 20)


(define (bob lst result)
  (if (null? lst)
      result
      (bob (cdr lst) (append result (list (+ 2 (car lst)))))
    )
)
(define (sue lst)
  (if (null? lst)
      '()
      (cons (* 2 (car lst)) (sue (cdr lst)))
     )
 )

(define (chooser op threshold)
  (lambda (x) ((eval op) x threshold))
  )