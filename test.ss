(define hello-world
  (lambda ()
    (begin
      (write 'Hello-World)
      (newline)
      (hello-world))))

(define add
  (lambda ()
    (begin
      (newline)
      (add))))
