local skynet = require "skynet"
local logger = require "skynet.xlog.core"
local debug = debug
local string_format = string.format
local skynet_error = skynet.error
local daemon = skynet.getenv("daemon")
local test = false

local _M = {}

function _M.debug(fmt, ...)
	local msg = string.format(fmt, ...)
	local info = debug.getinfo(2)
	if info then
		msg = string.format("[%s][%s:%d] %s", SERVICE_NAME, info.short_src, info.currentline, msg)
	end
	if test or daemon then
		logger.debug(SERVICE_NAME, msg)
	else
		local debug = string_format("[debug] %s", msg)
		skynet_error(debug)	
	end
end

function _M.info(fmt, ...)
	local msg = string.format(fmt, ...)
	local info = debug.getinfo(2)
	if info then
		msg = string.format("[%s][%s:%d] %s", SERVICE_NAME, info.short_src, info.currentline, msg)
	end
	if test or daemon then
		logger.info(msg)
	else
		local info = string_format("[info] %s", msg)
		skynet_error(info)	
	end
end

function _M.warn(fmt, ...)
	local msg = string.format(fmt, ...)
	local info = debug.getinfo(2)
	if info then
		msg = string.format("[%s:%d] %s", info.short_src, info.currentline, msg)
	end
	if test or daemon then
		skynet.send(logger, "lua", "warning", SERVICE_NAME, msg)
	else
		local info = string_format("[warn] %s", msg)
		skynet_error(info)
	end
end

function _M.error(fmt, ...)
	local msg = string.format(fmt, ...)
	local info = debug.getinfo(2)
	if info then
		msg = string.format("[%s:%d] %s", info.short_src, info.currentline, msg)
	end
	if test or daemon then
		skynet.send(logger, "lua", "error", SERVICE_NAME, msg)
	else
		local info = string_format("[error] %s", msg)
		skynet_error(info)
	end
end

function _M.fatal(fmt, ...)
	local msg = string.format(fmt, ...)
	local info = debug.getinfo(2)
	if info then
		msg = string.format("[%s:%d] %s", info.short_src, info.currentline, msg)
	end
	if test or daemon then
		skynet.send(logger, "lua", "fatal", SERVICE_NAME, msg)
	else
		local info = string_format("[fatal] %s", msg)
		skynet_error(info)
	end
end

return _M