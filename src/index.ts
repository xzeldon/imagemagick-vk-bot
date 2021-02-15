/* eslint-disable no-console */
import { VK, MessageContext } from 'vk-io';
import { HearManager } from '@vk-io/hear';

import { promisify } from 'util';

import { IImageMagick } from './interfaces';

// eslint-disable-next-line @typescript-eslint/no-var-requires
const im: IImageMagick = require('../build/Release/image.node');

const api = new VK({
	token: process.env.TOKEN as string
});

const hearManager = new HearManager<MessageContext>();

api.updates.on('message_new', hearManager.middleware);

api.updates.on('message_new', async (context, next) => {
	if (!context.hasAttachments('photo')) context.send('No images found!');
	return next();
});

hearManager.hear(/^jpeg$/, async (context) => {
	const img = context.getAttachments('photo')[0].largeSizeUrl;

	if (img) {
		console.time('Elasped');
		const processed_img = await promisify(im.jpeg)(img) as Buffer;
		console.timeEnd('Elasped');
		context.sendPhotos({
			value: processed_img
		});
	}
});

hearManager.hear(/^liquid$/, async (context) => {
	const img = context.getAttachments('photo')[0].largeSizeUrl;

	if (img) {
		console.time('Elasped');
		const processed_img = await promisify(im.liquid)(img, 'JPEG', 0) as Buffer;
		console.timeEnd('Elasped');
		context.sendPhotos({
			value: processed_img
		});
	}
});

api.updates.start().catch(console.error);
