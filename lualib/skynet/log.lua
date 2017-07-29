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
		logger.debug(msg)
	else
		local info = string_format("[debug] %s", msg)
		skynet_error(info)	
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

function _M.warning(fmt, ...)
	local msg = string.format(fmt, ...)
	local info = debug.getinfo(2)
	if info then
		msg = string.format("[%s:%d] %s", info.short_src, info.currentline, msg)
	end
	if test or daemon then
		logger.warning(msg)
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
		logger.error(msg)
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
		logger.fatal(msg)
	else
		local info = string_format("[fatal] %s", msg)
		skynet_error(info)
	end
end

return _M