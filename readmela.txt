New stuff to be aware of:

- Updated ms_strdup to return NULL in case of failloc instead of going to ms_error
	- (if it's too much trouble you can redo it and I'll find another way, probably containing int modus ;)
	- ms_itoa doesn't use data anymore
- data->currinput gets smaller now as the list gets filled, so don't use it pls
- data->currstr does not exist anymore
New parsing not finished, use oldparse in meantime