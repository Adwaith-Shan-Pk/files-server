const fs = require('fs').promises;
const path = require('path');

// Source directory for files to be listed
const filesDirectory = path.join(__dirname, 'public', 'files');
// Source HTML template
const templatePath = path.join(__dirname, 'template.html');
// Final output HTML file
const outputPath = path.join(__dirname, 'public', 'index.html');

// Helper function to get an emoji for a file type
function getFileEmoji(fileName) {
    const extension = path.extname(fileName).toLowerCase();
    switch (extension) {
        case '.pdf': return '📄';
        case '.jpg': case '.jpeg': case '.png': case '.gif': return '🖼️';
        case '.zip': case '.rar': case '.tar': case '.gz': return '📦';
        case '.pptx': case '.ppt': return '📊';
        case '.txt': case '.md': return '📝';
        case '.doc': case '.docx': return '📄';
        case '.c': return '👨‍💻';
        default: return '📁';
    }
}

async function buildStaticPage() {
    try {
        console.log('Starting static site build...');

        // Read the HTML template
        const template = await fs.readFile(templatePath, 'utf-8');

        // Read the contents of the files directory
        let fileListItems = '';
        try {
            const files = await fs.readdir(filesDirectory);
            console.log(`Found files: ${files.join(', ')}`);

            fileListItems = files.map(file => {
                const emoji = getFileEmoji(file);
                return `<li><a href="/files/${encodeURIComponent(file)}">${emoji} ${file}</a></li>`;
            }).join('');
        } catch (error) {
            console.log('Warning: "public/files" directory not found. Generating an empty list.');
            fileListItems = '<li>No files found. Add files to the "public/files" directory and rebuild.</li>';
        }

        const finalHtml = template.replace('<!-- FILE_LIST_PLACEHOLDER -->', fileListItems);
        await fs.writeFile(outputPath, finalHtml);
        console.log(`Successfully built static page to ${outputPath}`);
    } catch (error) {
        console.error('Error during build process:', error);
        process.exit(1);
    }
}

buildStaticPage();