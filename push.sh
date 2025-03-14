git remote remove origin 
git remote add origin https://github.com/mrmo7ox/minishell.git
git add .
git commit -m "$1"
git push -u origin master
git remote remove origin 
git remote add origin git@vogsphere-v2.1337.ma:vogsphere/intra-uuid-00f79a5f-a524-49ae-a0d4-de4749f28141-6405113-moel-oua
git add .
git commit -m "$1"
git push -u origin master