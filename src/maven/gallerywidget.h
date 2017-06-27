#ifndef GALLERYWIDGET_H
#define GALLERYWIDGET_H

#include "stable.h"
#include "mzSample.h"
#include "mainwindow.h"
#include "tabledockwidget.h"
#include "statistics.h"
#include "tinyplot.h"


class GalleryWidget : public QGraphicsView
{
    Q_OBJECT

		public:
				GalleryWidget(MainWindow* mw);
                ~GalleryWidget();

		public slots: 
            void replot();
			void clear() { scene()->clear(); plotitems.clear(); }
			void addEicPlots(std::vector<PeakGroup*>& groups);
			void addEicPlots(std::vector<Compound*>&compounds);
			void addEicPlots(std::vector<mzSlice*>&slices);
			void addEicPlots(std::vector<mzLink>&links);
            void addIdividualEicPlots(std::vector<EIC*>& eics,PeakGroup* grp);
            void fileGallery(const QString& dir);
            void exportPDF();

		private:
				MainWindow* mainwindow;
				QList<QGraphicsItem*> plotitems;
				int _rowSpacer;
				int _colSpacer;
				int _boxW;
				int _boxH;
				TinyPlot* addEicPlot(std::vector<EIC*>& eics);
                TinyPlot* addEicPlot(mzSlice& slice);
                bool recursionCheck;


		protected:
				void drawMap();
				void resizeEvent ( QResizeEvent *event );
				void wheelEvent(QWheelEvent *event);
                void mousePressEvent(QMouseEvent *event);
                void keyPressEvent(QKeyEvent *event);
                void contextMenuEvent(QContextMenuEvent * event);

};

#endif

