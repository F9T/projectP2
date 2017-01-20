function Component() {
     var programFiles = installer.environmentVariable("ProgramFiles");
     if (programFiles != "") {
		installer.setValue("TargetDir", programFiles + "/SpaceInvaders");
	 }
}