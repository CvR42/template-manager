.foreach c ${conslist ${typelist}}
s/\([a-zA-Z_][a-zA-Z0-9_]*\) *-> *$c\./to_$c(\1)->/g
.endforeach
