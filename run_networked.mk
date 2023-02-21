run_networked: $(APP)
	@if [ -z "$(HOST)" ]; then echo 'Set HOST variable first or use run_no_network'; else $(APP) -n; fi