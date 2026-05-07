# Branching and Commit Workflow

To satisfy the requested workflow of **4 branches**, **at least 5 commits**, and a **new-day commit**, use this plan:

## Branch Layout

1. `main` (stable)
2. `feature/attendance-core` (data model + add/remove/list)
3. `feature/attendance-sorting-search` (sort/search/update)
4. `feature/attendance-docs` (README/docs/comments)

## Example Commit Sequence (5+ commits)

1. `feat: scaffold attendance project`
2. `feat: add core attendance operations`
3. `feat: add sorting, search, update, persistence`
4. `docs: add usage and workflow documentation`
5. `chore: final validation and cleanup`

## New-Day Commit

Create the final commit on a different day by waiting until the next day, then:

```bash
git checkout feature/attendance-docs
git commit -m "chore: final polish on next day"
```

Then merge feature branches back to `main` through pull requests.
