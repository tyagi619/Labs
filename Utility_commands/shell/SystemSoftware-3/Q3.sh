cleanse()
{
	cd $1
	if [[ -e $1.EXE ]]; then
		rm $1.EXE
	fi
	if [[ -e $1.exe ]]; then
		rm $1.exe
	fi

	if [[ -e virusdefinition.virus ]]; then
		rm -f $(cat virusdefinition.virus)
		rm virusdefinition.virus
	fi

	for i in $(ls -1); do
		if [[ -d $i ]]; then
			cleanse $i
		fi
	done

	cd ..
}

cleanse $1