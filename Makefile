

.PHONY: quickpush git
quickgit:
	git add .
	git commit -m "git quick push"
	git push

git:
	git add.
	git commit -m "$(filter-out $@,$(MAKECMDGOALS))"
	git push
