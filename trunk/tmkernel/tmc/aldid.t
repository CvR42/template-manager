.. File: aldid.t
.. Tell need.t that this is for the ald template
.set template ald
.if ${len ${classlist}}
.error Class types not supported: ${seplist ", ", ${classlist}}
.exit 1
.endif
