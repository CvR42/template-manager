.. File: lluid.t
.. Tell need.t that this is for the llu template
.set template llu
.if ${len ${classlist}}
.error Class types not supported: ${seplist ", ", ${classlist}}
.exit 1
.endif
