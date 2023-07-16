## Standard Workflow

### Getting Started

1. Create a [new **Issue**](../../../issues/new) using the issue template

### Making Progress

2. Track the issue progress in the GitHub [**Project**](../../../projects)

3. If you are working locally, `git pull` any upstream changes

4. Create a new feature branch with an appropriate name
	> **Example**  
	> `git switch -c rc-filter`
 
5. Work on that branch, referencing the issue `#issueId` in commit messages as appropriate
	> **Example**  
	> `git commit -m "feat(rc-filter): add comparator (#issueId)"`

	> **Warning**  
	> Before you commit, ensure you `git pull`.  
	> After you commit, ensure you `git push`.
 
6. Once the feature is complete, `git push` your local changes

### Finishing Up

7. Open a [new **Pull Request**](../../../compare) into `main` using the Pull Request template that references the `#issueId` you are closing
	1. Assign yourself to the created **Pull Request**
	2. Request review from the other team members
 
8. Delete the feature branch

9. Move the issue card to `Done` in your Project

## Commit Conventions

- Consider following the [Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0/) specification