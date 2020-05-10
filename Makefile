CURRENT_DIRECTORY := $(abspath $(shell pwd))

SPACE :=
SPACE +=

.PHONY: phony_wildcard_target Makefile

# use a phony target as a pre-requisite for phony wildcard rules.
phony_wildcard_target:

# set empty Makefile target - otherwise will be processed by wildcard pattern.
Makefile:

# support invoking sub-makefiles in src/<submodule> directories.
%: phony_wildcard_target
	$(eval ARGS := $(subst :, ,$(MAKECMDGOALS)))
	$(eval SUBTARGET := $(firstword $(ARGS)))
	$(eval SUBARGS := $(wordlist 2, $(words $(ARGS)), $(ARGS)))
	$(eval SUBARGS := $(subst $(SPACE),:,$(SUBARGS)))
	${MAKE} -C src/$(SUBTARGET) $(SUBARGS)