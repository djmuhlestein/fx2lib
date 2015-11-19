#!/bin/bash

set -e

if [ "$TRAVIS" = true -a "$TRAVIS_SECURE_ENV_VARS" = false ]; then
	echo "No environment variables found, skipping (probably a pull request)."
	exit 0
fi

if [ "$TRAVIS" = true -a "$TRAVIS_BRANCH" != "master" ]; then
	echo "No master branch, skipping."
	exit 0
fi

if [ -z "$TRAVIS_REPO_SLUG" ]; then
	echo "No TRAVIS_REPO_SLUG value found."
	echo "Please set this if running outside Travis."
	exit 0
fi

# FIXME: Replace this with a deploy key, so you don't end up with tokens which
# potentially give people *a lot* of access to your GitHub repos.
if [ -z "$GH_TOKEN" ]; then
	echo "No GH_TOKEN value found."
	echo
	echo "Generate a GitHub token at https://github.com/settings/tokens/new"
	echo "with *only* the public_repo option."
	echo "Then go to https://travis-ci.org/$TRAVIS_REPO_SLUG/settings and"
	echo "add an 'Environment Variables' with the following;"
	echo " * Name == GH_TOKEN"
	echo " * Value == your token value from above"
	echo " * Display value in build log == OFF"
	echo
	echo "It is important that you protect this token, as it has full push"
	echo "access to your repos!"
	exit 1
fi

if [ -z "$GIT_NAME" ]; then
	echo "No GIT_NAME value found."
	echo
	echo "Then go to https://travis-ci.org/$TRAVIS_REPO_SLUG/settings and"
	echo "add an 'Environment Variables' with the following;"
	echo " * Name == GIT_NAME"
	echo " * Value == Human readable name for the commit author."
	echo "       Something like \"Tim Ansell's Robot\" is a good choice."
	echo " * Display value in build log == ON"
	exit 1
fi

if [ -z "$GIT_EMAIL" ]; then
	echo "No GIT_EMAIL value found."
	echo
	echo "Then go to https://travis-ci.org/$TRAVIS_REPO_SLUG/settings and"
	echo "add an 'Environment Variables' with the following;"
	echo " * Name == GIT_EMAIL"
	echo " * Value == Email address the commit author."
	echo "       Set up an email address, or use your own."
	echo " * Display value in build log == ON"
	exit 1
fi

TMPDIR=$(mktemp --directory)

if ! git describe > /dev/null 2>&1; then
	echo "- Fetching non shallow to get git version"
	git fetch --unshallow && git fetch --tags
fi
ORIG_GIT_REVISION=`git describe`
ORIG_COMMITTER_NAME=$(git log -1 --pretty=%an)
ORIG_COMMITTER_EMAIL=$(git log -1 --pretty=%ae)

echo "- Setting up the output"
cp -aRf docs/html/* $TMPDIR/
cp docs/intro/intro.pdf $TMPDIR/
find $TMPDIR | sort

echo "- Switching to the gh-pages branch"
git remote set-branches --add origin gh-pages
git fetch origin gh-pages
git checkout origin/gh-pages -b gh-pages

echo "- Updating the README"
sed -e"s-github.com/[^/]\+/[^/ ]\+-github.com/$TRAVIS_REPO_SLUG-" README.md > $TMPDIR/README.md
cat $TMPDIR/README.md

echo "- Adding the newly generated content"
rm -rf *
cp -aRf $TMPDIR/* .
git add -v -A .

echo "- Committing"
export GIT_AUTHOR_EMAIL="$ORIG_COMMITTER_EMAIL"
export GIT_AUTHOR_NAME="$ORIG_COMMITTER_NAME"
export GIT_COMMITTER_EMAIL="$GIT_NAME"
export GIT_COMMITTER_NAME="$GIT_EMAIL"
unset GIT_NAME
unset GIT_EMAIL
git commit -a -m "Travis build #$TRAVIS_BUILD_NUMBER of $ORIG_GIT_REVISION"

echo "- Pushing"
git remote set-url origin https://$GH_TOKEN@github.com/$TRAVIS_REPO_SLUG.git > /dev/null 2>&1
git push origin gh-pages > /dev/null 2>&1
