# The following directive works for most assemblers
#.section .text

.global _binary_ywresource_res
.global _binary_ywresource_res_size

# On OSX, if the directive above fails, comment it.
# and uncomment the following line
.section __DATA, __const

#
.balign 4
_binary_ywresource_res:
    .incbin "ywresource.res"
1:
_binary_ywresource_res_size:
.int 1b - _binary_ywresource_res
