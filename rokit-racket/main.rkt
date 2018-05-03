#lang racket

(module reader syntax/module-reader
  rokit-racket/rokit-racket-module
  #:wrapper1 (lambda (t)
               (define exp-t (t))
               
               (append exp-t
                       '((upload)))))

