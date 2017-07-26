local skynet = require "skynet"
local log = require "skynet.log"

skynet.start(function()
	skynet.fork(function ( ... )
		-- body
		while true do
			log.info("hell world.");
		end
	end)
	-- skynet.exit()
end)