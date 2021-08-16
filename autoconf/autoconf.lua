---
-- Autoconfiguration.
-- Copyright (c) 2016 Blizzard Entertainment
---
	local p = premake

	if not premake.modules.autoconf then
		p.modules.autoconf = {}
		p.modules.autoconf._VERSION = p._VERSION

		verbosef('Loading autoconf module...')
		include('api.lua')
		include('msc.lua')
		include('clang.lua')
		include('gcc.lua')
	end

	return p.modules.autoconf
