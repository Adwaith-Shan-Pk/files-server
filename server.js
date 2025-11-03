const express = require('express');
const fs = require('fs').promises;
const path = require('path');

const app = express();
const port = 3000;


const filesDirectory = path.join(__dirname, 'files');

function getFileEmoji(fileName) {
    const extension = path.extname(fileName).toLowerCase();
    switch (extension) {
        case '.pdf': return '📄';
        case '.jpg': case '.jpeg': case '.png': case '.gif': return '🖼️';
        case '.zip': case '.rar': case '.tar': case '.gz': return '📦';
        case '.pptx': case '.ppt': return '📊';
        case '.txt': case '.md': return '📝';
        case '.doc': case '.docx': return '📄';
        default: return '📁';
    }
}

app.use('/files', express.static(filesDirectory));


app.get('/', async (req, res) => {
    try {

        let template = await fs.readFile(path.join(__dirname, 'index.html'), 'utf-8');


        const files = await fs.readdir(filesDirectory);

        const fileListItems = files.map(file => {
            const emoji = getFileEmoji(file);
        
            return `<li><a href="/files/${encodeURIComponent(file)}">${emoji} ${file}</a></li>`;
        }).join('');

        
        const html = template.replace('<!-- File list will be dynamically generated here -->', fileListItems);

        res.send(html);
    } catch (error) {
        console.error('Error:', error);
        if (error.code === 'ENOENT') {
            let template = await fs.readFile(path.join(__dirname, 'index.html'), 'utf-8');
            const html = template.replace('<!-- File list will be dynamically generated here -->', '<li>No files found. Create a "files" directory and add some files.</li>');
            return res.send(html);
        }
        res.status(500).send('Error reading files directory.');
    }
});

app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);
});