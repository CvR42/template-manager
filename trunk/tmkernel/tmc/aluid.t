.. File: aluid.t
.. Tell need.t that this is for the alu template
.set template alu
.if ${len ${classlist}}
.error Class types not supported: ${seplist ", ", ${classlist}}
.exit 1
.endif
