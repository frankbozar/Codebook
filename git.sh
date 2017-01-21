git checkout master
git pull overleaf master --allow-unrelated-histories
git revert --mainline 1 HEAD
git push overleaf master

